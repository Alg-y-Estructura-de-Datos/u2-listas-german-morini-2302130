package src

import (
	"fmt"
	"math"
	"strconv"
)

type Fecha struct {
	Dia, Mes, Anio int
}

func (f *Fecha) EsBisiesto() bool {
	return (f.Anio%4 == 0 && f.Anio%100 != 0) || f.Anio%400 == 0
}

func (f *Fecha) String() string {
	return fmt.Sprintf("%d/%d/%d", f.Dia, f.Mes, f.Anio)
}

func Validar_fecha(fec Fecha) bool {
	var b bool = fec.Dia > 0

	switch fec.Mes {
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		return b && fec.Dia <= 31
	case 4:
	case 6:
	case 9:
	case 11:
		return b && fec.Dia <= 30
	case 2:
		if fec.EsBisiesto() {
			return b && fec.Dia <= 29
		}
		return b && fec.Dia <= 28
	default:
		return false
	}

	return false
}

func Fecha_validada(prompt string) Fecha {
	var fec Fecha

	for {
		print("   Dia: ")
		fec.Dia = Numero_validado(1, 31, prompt)

		print("   Mes: ")
		fec.Mes = Numero_validado(1, 12, prompt)

		print("   Año: ")
		fec.Anio = Numero_validado(math.MinInt32, math.MaxInt32, prompt)

		if !Validar_fecha(fec) {
			println("No es una fecha válida! Por favor, vuelva a ingresar una fecha")
			continue
		}
		return fec
	}
}

func Numero_validado(inicio int, fin int, prompt string) int {
	var n int
	var s string
	var err error

	for {
		fmt.Scan(&s)
		n, err = strconv.Atoi(s)
		if err != nil || n < inicio || n > fin {
			println("Ingrese un valor numerico entre", inicio, "-", fin)
			print(prompt)
		} else {
			break
		}
	}

	return n
}
