from fastapi import FastAPI, Form, HTTPException 
from fastapi.responses import HTMLResponse, RedirectResponse
from fastapi.staticfiles import StaticFiles
from id_work import Id_generator
from typing import Optional
from email_validator import validate_email, EmailNotValidError
import uvicorn
import json
import os

email = "my+address@example.org"


def load_comments_from_file():
    try:
        if os.path.exists("comments.json"):
            with open("comments.json", "r") as file:
                data = json.load(file)
                if not data:
                    return {}
                return data
        else:
            return {}
    except (json.JSONDecodeError, IOError):
        return {}


def save_comments_to_file(comments):
    try:
        with open("comments.json", "w") as file:
            json.dump(comments, file, indent = 4)
    except IOError as e:
        print(f"Error saving comments to file: {e}")


id_generator = Id_generator()
Dict_of_comments = load_comments_from_file()
for _ in range(len(Dict_of_comments)):
    id_generator.give_min_id()


app = FastAPI()
app.mount("/static", StaticFiles(directory = "static"), name = "static")


@app.get("/", response_class = HTMLResponse)
async def read_root():
    table_rows = "".join(
        f"<tr id='comment-{comment_id}'>"
        f"<td>{comment['email']}</td>"
        f"<td>{comment['text']}</td>"
        f"<td><form action='/delete_comment/{comment_id}' method='post'>"
        f"<button type='submit' class='delete-btn'>Delete</button>"
        f"</form></td>"
        f"</tr>"
        for comment_id, comment in Dict_of_comments.items()
    )


    content = f"""
    <!DOCTYPE html>
    <html>
    <head>
        <title>Comments_List</title>
        <link rel="stylesheet" href="/static/style.css">
    </head>
    <body>
        <h1>Comments_list</h1>

        <form action = "/add_comment" method = "post">  
            <input type = "email" name = "email" placeholder = "Your Email" required>
            <textarea name = "comment" placeholder = "Your Comment" required></textarea>
            <button type = "submit">Add Comment</button>
        </form>

        <form id = "filterForm">
            <input type = "text" id = "filterInput" placeholder = "Search comments..." onkeyup = "filterComments()">
        </form>

        <table>
            <thead>
                <tr>
                    <th>Email</th>
                    <th>Comment</th>
                    <th>Action</th>
                </tr>
            </thead>
            <tbody>
                {table_rows}
            </tbody>
        </table>
    <script src="/static/filter.js"></script>
    </body>
    </html>
    """
    return HTMLResponse(content, status_code = 200)

@app.post('/add_comment')
async def add_comment(
    email: str = Form(...),
    comment: str = Form(...)
):
    errors = []

    if not email:
        errors.append("Email is required")
    else:
        try:
            emailinfo = validate_email(email, check_deliverability = False)
        except EmailNotValidError as e:
            errors.append(str(e))

    if comment is None or comment.strip() == "":
        errors.append("Comment is required")

    if errors:
        raise HTTPException(status_code = 400, detail = errors)
    else:
        new_id = str(id_generator.give_min_id())
        Dict_of_comments[new_id] = {"email": email, "text": comment}
        save_comments_to_file(Dict_of_comments) 
    return RedirectResponse(url = "/", status_code = 303)

@app.post('/delete_comment/{comment_id}')
async def delete_comment(comment_id: str):
    if comment_id in Dict_of_comments:
        del Dict_of_comments[comment_id]
        id_generator.give_id_back(int(comment_id))
        save_comments_to_file(Dict_of_comments)
        return RedirectResponse(url = "/", status_code = 303)
    else:
        raise HTTPException(status_code = 404, detail = "Comment not found")

if __name__ == "__main__":
    uvicorn.run("main:app", host = "127.0.0.1", port = 8000, reload = True)
