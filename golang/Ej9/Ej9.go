package main

import (
	"Ej9/src"
	"fmt"
	"io"
	"net/http"
	"os"
	"os/exec"
)

var (
	historial []SitioWeb
	cursor    = 0
)

type SitioWeb struct {
	url       string
	html_file *os.File
}

func (sw *SitioWeb) abrir_sitio() error {
	err := exec.Command("firefox", sw.html_file.Name()).Start()
	if err != nil {
		println("Error al abrir el navegador:")
		println(err.Error())
		return err
	}

	return nil
}

func (sw *SitioWeb) destruir() error {
	return os.Remove(sw.html_file.Name())
}

func navegar(url string) error {
	// realizamos la consulta al sitio
	res, err := http.Get(url)
	if err != nil {
		println("No se pudo acceder al sitio:")
		println(err.Error())
		return err
	}

	// almacenamos el body de la consulta
	body, err := io.ReadAll(res.Body)
	if err != nil {
		println("No se pudo procesar el cuerpo de la consulta:")
		println(err.Error())
		return err
	}
	res.Body.Close()

	// creamos un archivo temporal
	tmpFile, err := os.CreateTemp("", "tmp-site*.html")
	if err != nil {
		println("No se pudo crear el archivo temporal:")
		println(err.Error())
		return err
	}

	// escribimos el body en el archivo
	_, err = tmpFile.Write(body)
	if err != nil {
		println("No se pudo crear el archivo temporal:")
		println(err.Error())
		return err
	}
	tmpFile.Close()

	sw := SitioWeb{url, tmpFile}

	// abrimos el archivo usando el navegador
	historial = append(historial, sw)
	return sw.abrir_sitio()
}

func aniadir() {
	var url string
	print("Ingrese la URL del sitio: ")
	fmt.Scan(&url)

	if err := navegar(url); err == nil {
		cursor++
	}
}

func mostrar_hist() {
	println("--- HISTORIAL ---")
	for i, sitio := range historial {
		if cursor == i {
			println("->", sitio.url)
		} else {
			println("  ", sitio.url)
		}
	}
}

func retroceder() {
	if cursor <= 0 {
		println("Estas en el primer sitio!")
		return
	}
	cursor--
}

func avanzar() {
	if cursor >= len(historial)-1 {
		println("Estas en el ultimo sitio!")
		return
	}
	cursor++
}

func eliminar_archivos() {
	for _, sitio := range historial {
		if err := sitio.destruir(); err != nil {
			println("Error al borrar el archivo", sitio.html_file.Name())
			println(err.Error())
		}
	}
}

func main() {
	var opt int
	var opciones = []func(){
		aniadir,
		mostrar_hist,
		retroceder,
		avanzar,
		func() { historial[cursor].abrir_sitio() },
		func() { eliminar_archivos(); os.Exit(0) },
	}

	// inicializa el navegador en google
	navegar("https://www.google.com")

	fmt.Println("\033[H\033[2J")
	for {
		println()
		println("🔎", historial[cursor].url)
		println()
		println("--- MENU ---")
		println("1. Agregar")
		println("2. Historial")
		println("3. Retroceder")
		println("4. Avanzar")
		println("5. Abrir")
		println("6. Salir")
		print("> ")
		opt = src.Numero_validado(1, len(opciones))
		fmt.Println("\033[H\033[2J")
		opciones[opt-1]()
	}
}
