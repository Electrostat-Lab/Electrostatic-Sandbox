const expandButton = document.getElementById('expandButton');
const menu = document.getElementById('navbar-collapse-with-animation');

// toggle events
expandButton.addEventListener('click', function() {
  menu.classList.toggle('hidden');
});
