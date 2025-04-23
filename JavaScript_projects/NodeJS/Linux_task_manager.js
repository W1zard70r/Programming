const { exec } = require("child_process");

exec("ps -eo ppid,pid,comm,args", (error, stdout, stderr) => {
    if (error) {
        console.log(`error: ${error.message}`);
        return;
    }
    if (stderr) {
        console.log(`stderr: ${stderr}`);
        return;
    }

    let lines = stdout.trim().split("\n");
    lines.shift();

    // создаём массив процессов
    let processes = lines.map(line => {
        let parts = line.trim().match(/^(\d+)\s+(\d+)\s+(\S+)\s+(.*)$/);
        if (!parts) return null; // Если строка не соответствует шаблону, пропускаем

        return {
            ppid: parseInt(parts[1], 10),  
            pid: parseInt(parts[2], 10),   
            name: parts[3],                
            command: parts[4] || "[no args]" 
        };
    }).filter(Boolean); // Убираем возможные null-значения
    
    // console.log(processes);

    // создаём дерево
    let makeTree = (array, ppid = 0) => {
        return array
            .filter(item => item.ppid === ppid)
            .map(item => ({
                ...item,
                children: makeTree(array, item.pid)
            }));
    };

    // Функция для вывода дерева в консоли
    let printTree = (nodes, prefix = "") => {
        nodes.forEach((node, index) => {
            let isLast = index === nodes.length - 1;
            let connector = isLast ? "└── " : "├── ";

            console.log(prefix + connector + "name = " + node.name + ", pid = " + node.pid + ", command = '" + node.command + "'");
            let newPrefix = prefix + (isLast ? "    " : "│   ");
            printTree(node.children, newPrefix);
        });
    };

    let tree = makeTree(processes)
    printTree(tree)

});
  