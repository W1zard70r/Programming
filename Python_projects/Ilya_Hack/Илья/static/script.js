function read_item() {
    location.href = `http://${location.host}/?search=${document.querySelector('#content_part').value}`
}
document.querySelector('#b3').addEventListener('click', read_item)

function add_message() {
    const new_message = JSON.stringify({ email: document.querySelector('#email').value, content: document.querySelector('#content').value });
    fetch(`/?new_message=${new_message}`, {
        method: 'POST',
    })
        .then(response => {
            if (!response.ok) {
                throw new Error('Network response was not ok');
            }
            return response.json();
        })
        .then(() => { location.reload() })
        .catch(error => {
            console.error('Error:', error);
            alert('Failed to add the message.');
        });
}
document.querySelector('#b1').addEventListener('click', add_message)



function delete_message() {
    const number = document.querySelector('#number').value;
    fetch(`/?number=${number}`, {
        method: 'DELETE',
    })
        .then(response => {
            if (!response.ok) {
                throw new Error('Network response was not ok');
            }
            return response.json();
        })
        .then(() => { location.reload() })
        .catch(error => {
            console.error('Error:', error);
            alert('Failed to delete the message.');
        });
}
document.querySelector('#b2').addEventListener('click', delete_message)
