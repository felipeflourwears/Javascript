import saludar, { CSaludar, PI, usuario } from "./constantes.js";
import { aritmetica as calculos } from "./aritmetica.js";
console.log("Archivo modulo.js");
console.log(PI, usuario);
//console.log(aritmetica.sumar(1, 2));
//console.log(aritmetica.restar(5, 4));
//Alias
console.log(calculos.sumar(1, 2));
console.log(calculos.restar(5, 4));
saludar();
let saludo = new CSaludar();
saludo;
