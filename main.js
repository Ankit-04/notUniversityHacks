
class Question {
    question;
    choices;
    correctAnswer;
 
    constructor(question, choices, correctAnswer) {
        this.question = question;
        this.choices = choices;
        this.correctAnswer = correctAnswer;
    }
}
 
var allQuestions = []
 
function onSubmit() {
    var correctAnswer = document.getElementById('answer').value
    if(correctAnswer > 5 || correctAnswer < 1){
        window.alert("Invalid answer chosen!");
        return;
    }
 
    var choiceArray = []
    choiceArray.push(`"${document.getElementById('choice1').value}"`);
    choiceArray.push(`"${document.getElementById('choice2').value}"`);
    choiceArray.push(`"${document.getElementById('choice3').value}"`);
    choiceArray.push(`"${document.getElementById('choice4').value}"`);
    choiceArray.push(`"${document.getElementById('choice5').value}"`);
 
    var question = new Question(document.getElementById('question').value, choiceArray, correctAnswer);
    allQuestions.push(question);
    convertQuestionToText(allQuestions);
}
 
function convertQuestionToText(question) {
    var number = question.length;
    var t = ` const byte arraySize = ${number}; <br><br> questionGroup question[arraySize] = {<br>`
    question.forEach(element => {
        t += `<pre>     {"${element.question}", [${element.choices}], ${element.correctAnswer}}<br></pre>`
    });
    t += `}`
    document.getElementById('textField').innerHTML = t;
}
 
 