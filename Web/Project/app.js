document.querySelectorAll('.extbtn').forEach((item) => {
  item.addEventListener('click', () => {
    alert('External Javascript affects the scriptable actions on multiple pages, Awesome!\nExternal Javascript is also best as it keeps HTML and Javascript separate')
  })
})