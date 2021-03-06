var W = window.innerWidth - 12, H = window.innerHeight - 12;

Module.onRuntimeInitialized = function () {
    if (document.readyState === 'complete') {
        onLoaded();
    } else {
        document.addEventListener('DOMContentLoaded', onLoaded);
    }
};

function onLoaded() {
    var filename = 'galaxy3.txt';
    var canvas = document.getElementById('canvas');
    var stats = new Stats();
    stats.showPanel(0);
    document.body.appendChild(stats.dom);

    var simulation = new Simulation(canvas, W, H, stats);
    simulation.start(filename);

    window.addEventListener('resize', function () {
        simulation.setDimensions(window.innerWidth - 12, window.innerHeight - 12);
    });

    var bodyDataSelect = document.getElementById('body-data');
    bodyDataSelect.addEventListener('change', function () {
        var filename = bodyDataSelect.options[bodyDataSelect.selectedIndex].value + '.txt';
        simulation.start(filename);
    });

    var timeStepInput = document.getElementById('time-step');
    timeStepInput.addEventListener('change', function () {
        var timeStep = parseFloat(timeStepInput.value);
        timeStep && simulation.setTimeStep(timeStep);
    });
}
