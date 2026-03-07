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