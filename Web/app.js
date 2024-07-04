document.querySelectorAll('.extbtn').forEach((item) => {
  item.addEventListener('click', () => {
    alert('External Javascript affects the scriptable actions on multiple pages, Awesome!\nExternal Javascript is also best as it keeps HTML and Javascript separate')
  })
})
// document.write('hello world');
// alert('hello world');
console.log("JavaScript is dynamically typed"); // writes to the console. Most powerful of the three
// let lesson, date;
// let lesson = "Canada on easy mode";
// console.log(lesson);
// let date = "March 10";
// lesson = "Today's date is";
// console.log(lesson, date);
// console.log("Hello, " + lesson + " " + date);
// const number = 34;
// let float = 2.466;
// console.log(float);
// float = 'Terrific!';
// console.log(float);

// let integer = 5;
// console.log(integer); // numbers will be colored blue or purple in the console
// integer = '5';
// console.log(integer); // strings will be black in the console
// operators += -= /= *= ++ -- %
// const add = num1 + num2;
// const sub = num1 - num2;
// const mult = num1 * num2;
// const div = num1 / num2; // 10 / 3 = 3.3333
// let number3 = '10';
// let number4 = '23';
// console.log(number3 - number4); // = -13 Implicit Type Conversion
// console.log(number3 - number4); // = 1023 String Concatenation
// number3 = parseInt(number3); // number3 = 10

// JavaScript data types
// Primitive - String, Number, Boolean, Null, Undefined, Symbol
// Object - Arrays, Functions, Objects
// typeof - operator (typeof variable) (typeof value) this returns the data type of the variable or value

// console.log(typeof null) returns object
// this is false, but it will never be fixed
// There is too much code that relies on the fact that null is an object in javascript
// const some_array = ['string', 'other string', 45, undefined, null];
// let abc = some_array[0];
// some_array[1] = 'some string';
// function script_kiddie(name){
//   console.log("hello script kiddie " + name);
//   return what;
// }
// script_kiddie(name);
// below is an example of function expression
// const add = function (num1, num2){
//   return num1 + num2;
// };
// const thirdValue = add(5, 6);
// In ES6, arrow functions were added
// const multiply = (num1, num2) => num1 * num2;
// function name = parameters => return value;

// yeah using app.js as the script for both index and about html's probably makes the 'website' bigger unnecessarily
// but this is just for notes and early practice

// const person = {
//   name:"john",
//   lastName:"mcclane",
//   age:40,
//   education:true,
//   married:true,
//   enemies:['Hans Gruber','Karl','Theo'],
//   greeting:function (){
//     console.log("NOW I HAVE A MACHINE GUN\nHO-HO-HO");
//   }
// }
// person.greeting();
// console.log(person.name, person.lastName);

// conditional statements
// ?? === !== ??
// == double equality checks only value === checks value and type
// const value = 2 > 1;
// const value2 = 1 > 2;
// typeof value = boolean
// 
// these two statments set value equal to num1 if the equality is passed
// const value = num1 == num2;
// const value = num1 === num2;
// text.length returns a length value
// text.toLowerCase();
// text.toUpperCase();
// text.charAt(0);
// text.indexOf('e'); returns number of first instace of e
// text.trim(); removes whitespace
// text.startsWith('partial string');
// text.includes('substring'); boolean
// text.slice(0, 1) returns the index of the string, i.e. substring, between 0 and 1.
// passing a negative value starts at the right end of the string and reads right to left
// 
// backticks are use to access template literals. backtick literals are more powerful than single quote?
// Interpolation ${} - insert expression(value)
// const name = 'raul';
// const age = 23;
// const sentence = `His name is ${name} and he is ${age} years old.`;
// 
// .concat() combines two arrays
// .reverse() reverses the array
// .unshift() shifts the item to the beginning of the array
// .shift() removes item from the beginning of the array
// .push() shifts to the end of the array
// .pop() removes from the end of the array
// .splice(param1, param2) grab specific items out of the array, mutates the original array. useful to know for react
// splice takes to parameters the index, and how many items to remove from the original 
// 
// both represent no value
// undefined - javascript can not find value for this
// variable without value
// missing function arguments
// missing object properties
// 
// null - developer sets the value
// 
// javascript checks for and uses local variables before checking global variables
// 
// Functions are first class objects - stored in a variable
// (expression), passed as an argument to another function, return
// from the function (closure)
// 
// Higher Order Function - accepts another function as an argument 
// or returns another function as a result
// 
// Callback function - passed to a function as an argument and executed inside that function
// 
// 