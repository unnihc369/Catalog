const fs = require('fs');

function calculateY(x, coefficients) {
    let y = 0;
    for (let i = 0; i < coefficients.length; i++) {
        y += coefficients[i] * Math.pow(x, i);
    }
    return y;
}

function generatePoints(n, k, c) {
    const points = [];
    const coefficients = new Array(k).fill(0).map((_, i) => (i === 0 ? c : Math.floor(Math.random() * 100))); // First coefficient is the secret

    for (let i = 1; i <= n; i++) {
        const x = i;
        const y = calculateY(x, coefficients);
        points.push({ x, y });
    }

    return points;
}

function savePointsToFile(points, filename) {
    const json = {
        keys: {
            n: points.length,
            k: points.length >= 2 ? 2 : points.length
        }
    };

    points.forEach((point, index) => {
        json[index + 1] = {
            base: "10",
            value: point.y.toString() // Saving in base 10
        };
    });

    fs.writeFileSync(filename, JSON.stringify(json, null, 2));
    console.log(`Points saved to ${filename}`);
}

// Usage Example
const n = 4; // Number of points
const k = 3; // Minimum points required to reconstruct the secret
const c = -20; // Secret value

const points = generatePoints(n, k, c);
console.log("Generated Points:");
points.forEach(point => console.log(`Point (x: ${point.x}, y: ${point.y})`));

savePointsToFile(points, 'points.json');
