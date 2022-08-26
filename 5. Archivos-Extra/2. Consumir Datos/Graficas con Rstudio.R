library(ggplot2)
library(readr)
datos <- read_csv("C:/Users/jejoc/OneDrive/Escritorio/Jeremy  ESPE/Software/Semestre SI MAY-SEP22/1. Estructura de Datos/Trabajos en C++/Nueva carpeta/datos.dat", 
                  col_types = cols(`0` = col_double()))
View(datos)

numeros <- datos$`0`
x <- numeros[1:40]
x1 <- numeros[41:45]

y0 <-x^{0} #grafica constante
plot(y0)
lines(y0)

y<-x #grafica lineal
plot(y, col="forestgreen")
lines(y, col="forestgreen")
 
y1<-x*x #grafica cuadratic
plot(y1, col="blue")
lines(y1, col="blue")

y2<-exp(x) #grafica exponencial
plot(y2, col="red")
lines(y2, col="red")

y3<-log(x) #grafica logaritmica
plot(y3)
lines(y3)

y4 <- factorial(x1)
plot(y4)
lines(y4)
