package main

import (
	"Ej6/src"
	"bufio"
	"database/sql"
	"fmt"
	"os"
	"strings"

	_ "github.com/mattn/go-sqlite3"
)

var (
	con     = make(map[string]Contacto)
	repo    *Repositorio
	scanner = bufio.NewScanner(os.Stdin)
	COLORES = map[string]string{
		"MAGENTA": "\033[35m",
		"ROJO":    "\033[31m",
		"VERDE":   "\033[32m",
		"AZUL":    "\033[34m",
		"CIAN":    "\033[36m",
	}
	PROMPT = COLORES["VERDE"] + "> \033[0m"
)

type Contacto struct {
	Nombre string
	Numero int
	DNI    int
}

func (c *Contacto) String() string {
	return fmt.Sprintf("%s %d %d", c.Nombre, c.DNI, c.Numero)
}

type Repositorio struct {
	conn *sql.DB
}

func GetInstance() *Repositorio {
	if repo == nil {
		var err error
		repo = &Repositorio{}

		repo.conn, err = sql.Open("sqlite3", "./contactos.db")
		if err != nil {
			println("No se pudo conectar a la base de datos")
			println(err.Error())
			os.Exit(2)
		}
	}

	return repo
}

func cargar() error {
	var tmp Contacto

	rows, err := repo.conn.Query("SELECT * FROM datos")
	if err != nil {
		return err
	}

	for rows.Next() {
		err := rows.Scan(&tmp.Nombre, &tmp.Numero, &tmp.DNI)
		if err != nil {
			continue
		}
		con[tmp.Nombre] = tmp
	}

	return nil
}

func guardar() error {
	_, err := repo.conn.Exec("DELETE FROM datos")
	if err != nil {
		return err
	}

	for _, val := range con {
		_, err = repo.conn.Exec("INSERT INTO datos VALUES (?,?,?)", val.Nombre, val.DNI, val.Numero)
		if err != nil {
			return err
		}
	}
	repo.conn.Close()

	return nil
}

func agregar_contactos() {
	println("¿Cuantos contactos desea agregar?")
	print(PROMPT)
	n := src.Numero_validado(0, 100, PROMPT)
	var tmp Contacto

	for i := 0; i < n; i++ {
		println("--- CONTACTO", i+1, "---")
		print("Nombre: ")
		scanner.Scan()
		tmp.Nombre = strings.TrimSpace(scanner.Text())

		print("DNI: ")
		tmp.DNI = src.Numero_validado(4000000, 70000000, PROMPT)

		print("Numero: ")
		tmp.Numero = src.Numero_validado(0, 2400000000, PROMPT)

		if _, ok := con[tmp.Nombre]; ok {
			println("El contacto ya existe!")
		} else {
			con[tmp.Nombre] = tmp
		}
	}
}

func mostrar() {
	println("--------------")
	for _, v := range con {
		println(v.String())
		println("--------------")
	}
}

func buscar() {
	var nom string
	print("Ingrese el nombre a buscar: ")
	scanner.Scan()
	nom = strings.TrimSpace(scanner.Text())

	c, ok := con[nom]
	if ok {
		println("Los datos son:", c.String())
	} else {
		println("El contacto no esta agendado!")
	}
}

func eliminar_contacto() {
	var nom string
	print("Ingrese el nombre a eliminar: ")
	scanner.Scan()
	nom = strings.TrimSpace(scanner.Text())

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

func inicializar() {
	repo = GetInstance()

	err := cargar()
	if err != nil {
		println("Error al iniciar el programa")
		fmt.Println(err)
		os.Exit(2)
	}
}

func terminar() {
	err := guardar()
	if err != nil {
		println("Error al terminar el programa")
		println(err.Error())
		os.Exit(2)
	}
}

func main() {
	inicializar()
	var operaciones = []func(){
		agregar_contactos,
		mostrar,
		buscar,
		eliminar_contacto,
		func() { println("Tenes", len(con), "contactos agendados!") },
		func() { terminar(); os.Exit(0) },
	}

	var opt int
	fmt.Println("\033[H\033[2J")
	for {
		println()
		println("--- MENU ---")
		println("1. Agregar")
		println("2. Mostrar")
		println("3. Buscar")
		println("4. Eliminar")
		println("5. Contar")
		println("6. Salir")
		print(PROMPT)

		opt = src.Numero_validado(1, 6, PROMPT)
		fmt.Println("\033[H\033[2J")
		operaciones[opt-1]()
	}
}
