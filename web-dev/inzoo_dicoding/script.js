function menuFunction() {
    var dropdown = document.getElementById("menu")
    if (dropdown.className === "menu") {
        dropdown.className += " responsive";
    } else {
        dropdown.className = "menu";
    }
}