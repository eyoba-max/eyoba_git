//console.log(`moges aklillu`);
document.getElementById("h1").textContent="eyob";
let userName;
document.getElementById("mySubmit").onclick=function(){
    userName=document.getElementById("myText").value;
    console.log(userName);
    document.getElementById("h1").textContent=`my name is ${userName}`;
}
let count=0;
document.getElementById("decrease").onclick=function(){
    count--;
    document.getElementById("lab").textContent=count;
}
document.getElementById("increase").onclick=function(){
    count=++count;
    document.getElementById("lab").textContent=count;
}
document.getElementById("reset").onclick=function(){
    count=0;
    document.getElementById("lab").textContent=count;
}

const subscribe=document.getElementById("subscribe");
const visaBtn=document.getElementById("visaBtn");
const paypalBtn=document.getElementById("paypalBtn");
const mastercardBtn=document.getElementById("mastercardBtn");
const submitBtn=document.getElementById("submitBtn");
const su=document.getElementById("sub");
const card=document.getElementById("ca");
submitBtn.onclick=function(){
if(subscribe.checked){
    su.textContent=`you are subscribed`;
}
else{
    su.textContent=`you are not subscribed`;
}
if(visaBtn.checked){
    card.textContent=`you selected visa`;
}
else if(paypalBtn.checked){
    card.textContent=`you selected paypal`;
}
else if(mastercardBtn.checked){
    card.textContent=`you selected mastercard`;
}
else{
    card.textContent=`you didn't select any payment method`;
}

}
/*
const minNum=1;
const maxNum=100;
const answer=Math.floor(Math.random()*(maxNum-minNum)+minNum);

let attempts=0;
let guess;
let running=true;

while(running){
    guess=window.prompt(`guess a number between ${minNum}-${maxNum}`);
    guess=Number(guess);
    if(isNaN(guess)){
        window.alert("please enter a valid number");
    }
    else if(guess<minNum || guess>maxNum){
        window.alert("please enter a number between the given range");
    }
    else{
       attempts++; 
       if(guess<answer){
        window.alert("TOO LOW TRY AGAIN!!");
       }
       else if(guess>answer){
        window.alert("TOO HIGH TRY AGAIN!!");
       }
       else{
        window.alert(`CORRECT! The answer was ${answer} you tried ${attempts} times.`);
        running=false;
       }
    }
    
}*/
let toggle = document.getElementById("toggle");

toggle.onclick = function() {
    if (document.body.style.backgroundColor === "black") {
        document.body.style.backgroundColor = "white"; // Change back to white
        document.body.style.colr="black";
    } else {
        document.body.style.backgroundColor = "black"; // Change to black
    }
};

