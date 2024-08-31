package main

import (
	"Ejercicios/src"
	"fmt"
	"os"
)

var (
	con = make(map[string]int)
)

type Contacto struct {
	Nombre string
	Numero int
}

func (c *Contacto) String() string {
	return fmt.Sprintf("%s %d", c.Nombre, c.Numero)
}

func cargar(f string) error {
	file, err := os.Open(f)
	if err != nil {
		return err
	}
	defer file.Close()

	var tmp Contacto
	for {
		_, err := fmt.Fscanf(file, "%s %d\n", &tmp.Nombre, &tmp.Numero)
		if err != nil {
			break
		}

		if _, ok := con[tmp.Nombre]; !ok {
			con[tmp.Nombre] = tmp.Numero
		}
	}

	return nil
}

func guardar(f string) error {
	// file, err := os.Create(f)
	file, err := os.OpenFile(f, os.O_WRONLY|os.O_CREATE|os.O_TRUNC, 0777)
	if err != nil {
		return err
	}
	defer file.Close()

	for k, v := range con {
		file.WriteString(fmt.Sprintf("%s %d\n", k, v))
	}

	return nil
}

func agregar_contactos() {
	println("¿Cuantos contactos desea agregar?")
	print("> ")
	n := src.Numero_validado(0, 100)
	var tmp Contacto

	for i := 0; i < n; i++ {
		println("--- CONTACTO", i+1, "---")
		print("Nombre: ")
		fmt.Scan(&tmp.Nombre)

		print("Numero: ")
		tmp.Numero = src.Numero_validado(0, 2400000000)

		if _, ok := con[tmp.Nombre]; !ok {
			con[tmp.Nombre] = tmp.Numero
		} else {
			println("El contacto ya existe!")
		}
	}
}

func mostrar() {
	println("--------------")
	for k, v := range con {
		println(k)
		println(v)
		println("--------------")
	}
}

func buscar() {
	var nom string
	print("Ingrese el nombre a buscar:")
	fmt.Scan(&nom)

	num, ok := con[nom]
	if ok {
		println("El contacto tiene numero", num)
	} else {
		println("El contacto no esta agendado!")
	}
}

func eliminar_contacto() {
	var nom string
	print("Ingrese el nombre a eliminar:")
	fmt.Scan(&nom)

	_, ok := con[nom]
	if !ok {
		println("El contacto no esta agendado!")
		return
	}
	delete(con, nom)

	_, ok = con[nom]
	if !ok {
		println("Contacto eliminado")
	} else {
		println("No se pudo eliminar el contacto!")
	}
}

func main() {
	err := cargar("contactos.txt")
	if err != nil {
		panic(err)
	}

	var operaciones = []func(){
		agregar_contactos,
		mostrar,
		buscar,
		eliminar_contacto,
		func() { println("Tenes", len(con), "contactos agendados!") },
		func() { guardar("contactos.txt"); os.Exit(0) },
	}

	var opt int
	for {
		println()
		println("--- MENU ---")
		println("1. Agregar")
		println("2. Mostrar")
		println("3. Buscar")
		println("4. Eliminar")
		println("5. Contar")
		println("6. Salir")
		print("> ")

		opt = src.Numero_validado(1, 6)
		operaciones[opt-1]()
	}
}
