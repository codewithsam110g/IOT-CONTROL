document.addEventListener("DOMContentLoaded", function() {
  const buttons = document.querySelectorAll(".relay-btn");

  buttons.forEach(button => {
    button.addEventListener("click", function() {
      const relayNum = this.getAttribute("data-relay");
      toggleRelay(relayNum);
    });
  });

  function toggleRelay(relayNum) {
    const xhr = new XMLHttpRequest();
    xhr.open("GET", `/toggleRelay/${relayNum}`, true);
    
    xhr.onload = function() {
      if (xhr.status === 200) {
        console.log(`Successfully toggled relay ${relayNum}`);
      } else {
        console.error(`Failed to toggle relay ${relayNum}`);
      }
    };
    
    xhr.onerror = function() {
      console.error("Request error");
    };

    xhr.send();
  }
});
