let slideIndex = 0;
let isAutoSliding = true; // Flag to control auto sliding
showSlides();

function showSlides() {
    let slides = document.getElementsByClassName("mySlides");
    let dots = document.getElementsByClassName("dot");

    // Hide all slides
    for (let i = 0; i < slides.length; i++) {
        slides[i].style.display = "none";
    }

    slideIndex++;
    if (slideIndex > slides.length) {
        slideIndex = 1; // Reset to the first slide if we're at the end
    }

    // Remove active class from all dots
    for (let i = 0; i < dots.length; i++) {
        dots[i].className = dots[i].className.replace(" active", "");
    }

    // Show the current slide and add active class to the corresponding dot
    slides[slideIndex - 1].style.display = "block";
    dots[slideIndex - 1].className += " active";

    // Automatically cycle through slides if isAutoSliding is true
    if (isAutoSliding) {
        setTimeout(showSlides, 4000); // Change image every 4 seconds
    }
}

// Function to set current slide when a dot is clicked
function currentSlide(n) {
    slideIndex = n; // Set the current slide index to the clicked dot index
    isAutoSliding = false; // Stop auto sliding
    showSlides(); // Show the selected slide

    // Restart auto sliding after 3.5 seconds
    setTimeout(() => {
        isAutoSliding = true; // Re-enable auto sliding
        showSlides(); // Resume slideshow
    }, 4000); // Adjust delay as needed
}
