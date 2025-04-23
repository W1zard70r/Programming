import json
import uvicorn
from email_validator import validate_email, EmailNotValidError
from fastapi.staticfiles import StaticFiles
from fastapi.responses import HTMLResponse
from fastapi import FastAPI, Request, HTTPException
from fastapi.templating import Jinja2Templates
from slowapi import Limiter
from slowapi.util import get_remote_address
from slowapi.errors import RateLimitExceeded

app = FastAPI()


limiter = Limiter(key_func=get_remote_address)
app.state.limiter = limiter

app.mount("/static", StaticFiles(directory="static"))
templates = Jinja2Templates(directory = "templates")

try:
    with open("data.json", "r", encoding="utf-8") as f:
        file_content = f.read().strip()
        if not file_content:
            messages = []
        else:
            messages = json.loads(file_content)
except FileNotFoundError:
    messages = []
except json.JSONDecodeError:
    messages = []


@app.exception_handler(RateLimitExceeded)
async def rate_limit_exceeded_handler(request: Request, exc: RateLimitExceeded):
    return templates.TemplateResponse(
        request=request,
        name="index.html",
        context={
            "messages": [
                {"email": "Our server is overloaded", "content": "please, try later"}
            ]
        },
        # добавил строчку ниже
        status_code = 429
    )


@app.get("/", response_class=HTMLResponse)
@limiter.limit("20/minute")
async def read_item(request: Request, search: str | None = None):
    if not search:
        return templates.TemplateResponse(
            request=request, name="index.html", context={"messages": messages}
        )
    else:
        filtered_messages = list(
            filter(
                lambda message: search.lower().replace(" ", "")
                in message["content"].lower().replace(" ", ""),
                messages,
            )
        )
        if filtered_messages == []:
            filtered_messages.append(
                {
                    "email": "Sorry",
                    "content": "nothing found",
                }
            )
        return templates.TemplateResponse(
            request=request, name="index.html", context={"messages": filtered_messages}
        )


@app.post("/", tags=["messages"], summary="add message")
async def add_message(new_message: str):
    # тут Илья преобразует query параметр new_message из str в json
    # added_message = json.loads(new_message)
    # может получиться так, что new_message не json а какая-то фигня или его вообще нет
    # вариант исправления
    try:
        added_message = json.loads(new_message)
    except:
        raise HTTPException(status_code = 404, detail = "the 'new_message' is not json")
    

    try:
        validate_email(added_message["email"])
        if len(added_message["content"]) <= 100 and len(added_message["email"]) <= 100:
            messages.append(added_message)
            if len(messages) > 50:
                messages.pop(0)
        with open("data.json", "w", encoding="utf-8") as file:
            json.dump(messages, file)
        return {"success": "Your message was added to the list!"}
    except EmailNotValidError:
        return {"success": "This email does not exist!"}


@app.delete("/", tags=["messages"], summary="delete message")
async def delete_message(number: str):
    try:
        if int(number) - 1 >= 0:
            messages.pop(int(number) - 1)
        with open("data.json", "w", encoding="utf-8") as file:
            json.dump(messages, file)
        return {"success": "The element was deleted"}
    except IndexError:
        return {"success": "The element does not exist"}
    except ValueError:
        return {"success": "The element does not exist"}


if __name__ == "__main__":
    uvicorn.run(
        "main:app",
        host="127.0.0.1",
        port=8080,
        reload=True,
        timeout_keep_alive=60,
        timeout_graceful_shutdown=10,
    )
