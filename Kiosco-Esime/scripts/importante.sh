#!/bin/bash

if [ -e ../Recursos/otros/eventos.txt ] 
then
	rm ../Recursos/otros/eventos.txt
	ls ../Recursos/eventos/importante/ >> ../Recursos/otros/eventos.txt
else
	touch ../Recursos/otros/eventos.txt
	ls ../Recursos/eventos/importante/ >> ../Recursos/otros/eventos.txt
fi
