const socket = io();

socket.on('temp', function(data) {
    console.log(`Temperature: ${data}`);
    let temp = document.getElementById('temperature');
    temp.innerHTML = `${data}°C`;
})
socket.on('humidity', function(data) {
    console.log(`Humidity: ${data}`);
    let temp = document.getElementById('humidity');
    temp.innerHTML = `${data}%`;
})
socket.on('light', function(data) {
    console.log(`Light: ${data}`);
    if(data > 200) {
        document.getElementById("body").classList.add('dark');
    } else {
        document.getElementById("body").classList.add('light');
    }
    temp.innerHTML = `${data}%`;
})