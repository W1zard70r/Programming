def evaluate_expression(s):
    s = s.replace(" ", "")
    
    s = s.replace("(-", "(0-")
    while "--" in s:
        s = s.replace("--", "+")
    if s.startswith("-"):
        s = "0" + s
    
    def evaluate(tokens):
        stack = []
        num = 0
        sign = '+'
        i = 0
        while i < len(tokens):
            char = tokens[i]
            if char.isdigit():
                num = num * 10 + int(char)
            elif char == '(':
                balance = 1
                j = i + 1
                while j < len(tokens) and balance != 0:
                    if tokens[j] == '(':
                        balance += 1
                    elif tokens[j] == ')':
                        balance -= 1
                    j += 1
                num = evaluate(tokens[i+1:j-1])
                i = j - 1
            if i == len(tokens) - 1 or char in '+-':
                if sign == '+':
                    stack.append(num)
                elif sign == '-':
                    stack.append(-num)
                sign = char
                num = 0
            i += 1
        return sum(stack)
    
    return evaluate(s)

S = input().strip()
print(evaluate_expression(S))