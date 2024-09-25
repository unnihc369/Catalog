const fs = require('fs');

function decodeValue(value, base) {
    return parseInt(value, base);
}

function lagrangeInterpolation(points) {
    let result = 0;
    const k = points.length;

    for (let i = 0; i < k; i++) {
        let term = points[i].y;
        for (let j = 0; j < k; j++) {
            if (i !== j) {
                term *= (0 - points[j].x) / (points[i].x - points[j].x);
            }
        }
        //console.log(term)
        result += term;
    }

    return result;
}

function findSecret(filename) {
    const rawData = fs.readFileSync(filename);
    const jsonData = JSON.parse(rawData);

    console.log("Checkpoint 1: Read test case json");
    console.log(jsonData);

    const points = [];
    console.log("Checkpoint 2: Decode Y values using given base");

    for (const key in jsonData) {
        if (key === 'keys') continue;

        const x = parseInt(key);
        const base = parseInt(jsonData[key].base);
        const value = jsonData[key].value;

        const y = decodeValue(value, base);

        console.log(`Decoded point: (${x}, ${y})`);

        points.push({ x, y });
    }

    const secret = lagrangeInterpolation(points);

    console.log("Checkpoint 3: Find the Secret (C)");
    console.log("The secret is:", secret);
}

findSecret('input.json');