const expandButton = document.getElementById('expandButton');
const menu = document.getElementById('navbar-collapse-with-animation');

// toggle events
expandButton.addEventListener('touchstart', function() {
  menu.classList.toggle('hidden');
  menu.classList.toggle('overflow-hidden');
  menu.classList.toggle('hs-collapse');
});

expandButton.addEventListener('click', function() {
  menu.classList.toggle('hidden');
  menu.classList.toggle('overflow-hidden');
  menu.classList.toggle('hs-collapse');
});
