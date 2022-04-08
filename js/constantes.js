export const PI = Math.PI;
export let usuario = "Felipe";

const password = "qwerty";
//export default password;
const hello = () => console.log("Hello"); //Funcion expresadas guardadas en variables

export default function saludar() {
  //Funcion definida
  console.log("Hola modulos+ES6");
}
export class CSaludar {
  constructor() {
    console.log("Hola Clases+ES6");
  }
}
