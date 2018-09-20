function arrayToPtr(array) {
    var ptr = Module._malloc(array.length * Float64Array.BYTES_PER_ELEMENT);
    Module.HEAPF64.set(array, ptr / Float64Array.BYTES_PER_ELEMENT);
    return ptr;
}

function ptrToArray(ptr, length) {
    var array = new Float64Array(length);
    var pos = ptr / Float64Array.BYTES_PER_ELEMENT;
    array.set(Module.HEAPF64.subarray(pos, pos + length));
    return array;
}

function getData(filename) {
    return fetch('inputs/' + filename)
        .then(function (response) {
            return response.text();
        })
        .then(function (text) {
            var lines = text.split('\n');
            var radius = parseFloat(lines[1]);

            var xPos = [], yPos = [], xVel = [], yVel = [], mass = [];
            lines.slice(2, lines.length - 1).forEach(function (line) {
                var splitted = line.split(' ');
                xPos.push(parseFloat(splitted[0]));
                yPos.push(parseFloat(splitted[1]));
                xVel.push(parseFloat(splitted[2]));
                yVel.push(parseFloat(splitted[3]));
                mass.push(parseFloat(splitted[4]));
            });
            return {
                radius: radius,
                xPos: xPos,
                yPos: yPos,
                xVel: xVel,
                yVel: yVel,
                mass: mass
            };
        });
}

function getColor(value) {
    var hue = 250 + (value * (320 - 250));
    return ["hsl(", hue, ",100%,50%)"].join("");
}

function Simulation(canvas, _width, _height, stats) {
    var self = this;
    var ctx = canvas.getContext('2d');
    var requestAnimationId = null;
    var xMin, xMax, yMin, yMax, xPos, yPos, length, maxMass, particleMassColor;
    var xPosBuf, yPosBuf, xVelBuf, yVelBuf, massBuf;
    var dt = 0.1, width = _width, height = _height;

    canvas.width = width;
    canvas.height = height;

    function scaleX(x) {
        return width * (x - xMin) / (xMax - xMin);
    }

    function scaleY(y) {
        return height * (y - yMin) / (yMax - yMin);
    }

    function clearBackground() {
        ctx.save();
        ctx.fillStyle = '#111';
        ctx.fillRect(0, 0, width, height);
        ctx.fill();
        ctx.restore();
    }

    function drawBodies() {
        clearBackground();
        for (var i = 0; i < length; i++) {
            var x = scaleX(xPos[i]), y = scaleY(yPos[i]);

            ctx.save();
            ctx.shadowBlur = 10;
            ctx.fillStyle = particleMassColor[i];
            ctx.shadowColor = particleMassColor[i];
            ctx.beginPath();
            ctx.arc(x, H - y, 3, 0, 2 * Math.PI);
            ctx.closePath();
            ctx.fill();
            ctx.restore();
        }
    }

    function simulate() {
        stats.begin();

        Module._step(dt);
        var xPosPtr = Module._getXPos(), yPosPtr = Module._getYPos();
        xPos = ptrToArray(xPosPtr, length);
        yPos = ptrToArray(yPosPtr, length);
        drawBodies();

        Module._free(xPosPtr);
        Module._free(yPosPtr);

        stats.end();
        requestAnimationId = requestAnimationFrame(simulate);
    }

    function startSimulation(data) {
        xMin = -data.radius;
        xMax = data.radius;
        yMin = -data.radius;
        yMax = data.radius;

        xPosBuf = arrayToPtr(data.xPos);
        yPosBuf = arrayToPtr(data.yPos);
        xVelBuf = arrayToPtr(data.xVel);
        yVelBuf = arrayToPtr(data.yVel);
        massBuf = arrayToPtr(data.mass);
        length = data.xPos.length;
        xPos = data.xPos;
        yPos = data.yPos;

        Module._init(length, xPosBuf, yPosBuf, xVelBuf, yVelBuf, massBuf, data.radius);

        maxMass = data.mass.reduce(function (p, v) {
            return (p >= v ? p : v);
        });
        particleMassColor = data.mass.map(function (mass) {
            return getColor(mass / maxMass);
        });
        simulate();
    }

    self.start = function (filename) {
        self.stop();
        clearBackground();
        getData(filename).then(startSimulation);
    };

    self.stop = function () {
        requestAnimationId && cancelAnimationFrame(requestAnimationId);
        xPosBuf && Module._free(xPosBuf);
        yPosBuf && Module._free(yPosBuf);
        xVelBuf && Module._free(xVelBuf);
        yVelBuf && Module._free(yVelBuf);
        massBuf && Module._free(massBuf);
    };

    self.setDimensions = function (_width, _height) {
        width = _width;
        height = _height;
        canvas.width = width;
        canvas.height = height;
    };

    self.setTimeStep = function (timeStep) {
        dt = timeStep;
    };
}