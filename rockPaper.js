function pickComputerMove(){
    const randomNum=Math.random();
    let computerMove='';
    if(randomNum>=0 && randomNum<1/3){
        computerMove='rock';
    }
    else if(randomNum>=1/3 && randomNum<2/3){
        computerMove='paper';
    }
    else if(randomNum>=2/3 && randomNum<1){
        computerMove='scissor';
    }
    return computerMove;
}

function playGame(playerMove){
    const computerMove=pickComputerMove();
    let result='';
    if(playerMove==='scissor'){
        if(computerMove==='rock'){
            result='you lose';
        }
        else if(computerMove==='paper'){
            result='you win';
        }
        else if(computerMove==='scissor'){
            result='tie';
        }
    }
     else if(playerMove==='paper'){
        if(computerMove==='rock'){
            result='you win';
        }
        else if(computerMove==='paper'){
            result='tie';
        }
        else if(computerMove==='scissor'){
            result='you lose';
        }
    }
    else if(playerMove==='rock'){
        if(computerMove==='rock'){
            result='tie';
        }
        else if(computerMove==='paper'){
            result='you lose';
        }
        else if(computerMove==='scissor'){
            result='you win';
        }
    }
alert(`you picked ${playerMove}. Computer picked ${computerMove}. ${result}`);
}

const display=document.getElementById("display");
function appendToDisplay(input){
    display.value+=input;
}
function clearDisplay(){
    display.value='';
}
function calculate(){
    try{
        display.value=eval(display.value);
    }
    catch{
        display.value="error!!";
    }
}