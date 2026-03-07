//console.log(`moges aklillu`);
document.getElementById("h1").textContent="eyob";
let userName;
document.getElementById("mySubmit").onclick=function(){
    userName=document.getElementById("myText").value;
    console.log(userName);
    document.getElementById("h1").textContent=`my name is ${userName}`;
}
let count;
document.getElementById("decrease").onclick=function(){
    count--;
    document.getElementById("lab").textContent=count;
}
document.getElementById("increase").onclick=function(){
    count=2+count;
    document.getElementById("lab").textContent=count;
}
document.getElementById("reset").onclick=function(){
    count=0;
    document.getElementById("lab").textContent=count;
}

const subscribe=document.getElementById("subscribe");
const visaBtn=document.getElementById("visaBtn");
const paypalBtn=document.getElementById("vpaypalBtn");
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