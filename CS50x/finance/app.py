import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]

    transactions_db = db.execute(
        "SELECT symbol,SUM(shares) AS shares, price FROM transactions WHERE user_id = ? GROUP BY symbol", user_id)
    cash_db = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
    cash = cash_db[0]["cash"]

    return render_template("index.html", database=transactions_db, cash=cash)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "GET":
        return render_template("buy.html")
    else:
        symbol = request.form.get("symbol")
        shares_input = request.form.get("shares")

        # Validate stock symbol
        if not symbol:
            return apology("Must provide a Stock Symbol")

        stock = lookup(symbol.upper())
        if stock is None:
            return apology("Please provide a valid stock symbol")

        # Validate shares input
        try:
            shares = int(shares_input)
            if shares <= 0:
                return apology("Shares must be a positive integer")
        except ValueError:
            return apology("Shares must be a valid integer")

        # Calculate transaction value and check user funds
        transaction_value = shares * stock["price"]
        user_id = session["user_id"]
        user_cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

        if user_cash < transaction_value:
            return apology("Insufficient funds")

        # Update user's cash and log transaction
        uptd_cash = user_cash - transaction_value
        db.execute("UPDATE users SET cash = ? WHERE id = ?", uptd_cash, user_id)
        date = datetime.datetime.now()
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price, date) VALUES (?, ?, ?, ?, ?)",
                   user_id, stock["symbol"], shares, stock["price"], date)

        flash(f"Stock purchased at ${stock['price']:.2f} || Cash: {uptd_cash:.2f}")
        return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    user_id = session["user_id"]
    transactions_db = db.execute("SELECT * FROM transactions WHERE user_id = ?", user_id)
    return render_template("history.html", transactions=transactions_db)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "GET":
        return render_template("quote.html")

    else:
        symbol = request.form.get("symbol")

        if not symbol:
            return apology("Must provide a Stock Symbol")
        stock = lookup(symbol.upper())
        if stock == None:
            return apology("Please Provide Valid Stock Symbol")

        return render_template("quoted.html", name=stock["name"], price=stock["price"], symbol=stock["symbol"])


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Get username and password from the form
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Ensure username was submitted
        if not username:
            return apology("must provide username")

        # Ensure password was submitted
        if not password:
            return apology("must provide password")

        if not confirmation:
            return apology("must provide confirmation of password")

        if confirmation != password:
            return apology("passwords do not match!")

        hash = generate_password_hash(password)

        try:
            new_user = db.execute(
                "INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)
        except:
            return apology("username already taken")

        session["user_id"] = new_user  # Remember which user has logged in

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "GET":
        user_id = session["user_id"]
        # Retrieve all symbols the user owns with the total shares
        symbols_user = db.execute(
            "SELECT symbol, SUM(shares) AS total_shares FROM transactions WHERE user_id = ? GROUP BY symbol HAVING total_shares > 0", user_id)
        return render_template("sell.html", symbols=[row["symbol"] for row in symbols_user])

    else:
        symbol = request.form.get("symbol")
        shares_input = request.form.get("shares")

        if not symbol:
            return apology("Must provide a Stock Symbol")
        stock = lookup(symbol.upper())

        if stock is None:
            return apology("Please Provide Valid Stock Symbol")

        # Validate shares input
        try:
            shares = int(shares_input)
            if shares <= 0:
                return apology("Please enter a positive number of shares you would like to sell")
        except ValueError:
            return apology("Please enter a valid integer for shares")

        # Get the user's current shares for the selected symbol
        user_id = session["user_id"]
        user_shares = db.execute(
            "SELECT SUM(shares) AS total_shares FROM transactions WHERE user_id = ? AND symbol = ? GROUP BY symbol", user_id, symbol)

        # Ensure that user_shares is not empty and that they have enough shares
        if not user_shares or user_shares[0]["total_shares"] < shares:
            return apology("You don't have this amount of shares")

        # Calculate transaction value
        transaction_value = shares * stock["price"]

        # Update user's cash
        user_cash_db = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        user_cash = user_cash_db[0]["cash"]
        uptd_cash = user_cash + transaction_value
        db.execute("UPDATE users SET cash = ? WHERE id = ?", uptd_cash, user_id)

        # Log the transaction
        date = datetime.datetime.now()
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price, date) VALUES (?, ?, ?, ?, ?)",
                   user_id, stock["symbol"], -shares, stock["price"], date)

        flash(f"Stock Sold! || Cash: ${uptd_cash:.2f}")
        return redirect("/")


@app.route("/addcash", methods=["GET", "POST"])
@login_required
def addcash():
    """User adding Cash"""
    if request.method == "GET":
        return render_template("addcash.html")

    else:
        new_cash = int(request.form.get("new_cash"))

        if not new_cash:
            return apology("Please enter a cash amount")

        user_id = session["user_id"]
        user_cash_db = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        user_cash = user_cash_db[0]["cash"]

        uptd_cash = user_cash + new_cash
        db.execute("UPDATE users SET cash = ? WHERE id = ?", uptd_cash, user_id)

        flash(f"${new_cash} added to account")

        return redirect("/")
