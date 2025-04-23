function filterComments() {
    const filterValue = document.getElementById('filterInput').value.toLowerCase();
    const rows = document.querySelectorAll('table tbody tr');

    rows.forEach(row => {
        const emailCell = row.cells[0].textContent.toLowerCase();
        const commentCell = row.cells[1].textContent.toLowerCase();

        if (emailCell.includes(filterValue) || commentCell.includes(filterValue)) {
            row.style.display = '';  
        } else {
            row.style.display = 'none';  
        }
    });
}
