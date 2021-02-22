(defrule leer-sangre-temp
(declare (salience 2))
(initial-fact)
=>
(printout t “Indique la temperatura de la sangre (fria, caliente)“ crlf)
(assert (sangre-temp (read)))
)

(defrule leer-piel
(declare (salience 2))
(initial-fact)
=>
(printout t “Indique cómo es la piel (con-pelo, con-plumas, con-escamas, porosa)“ crlf)
(assert (piel (read)))
)

(defrule anfibio
(declare (salience 3))
(piel porosa)
(sangre-temp fria)
=>
(printout t “Es un anfibio“ crlf)
(assert(animal anfibio))
)

(defrule reptil
(declare (salience 3))
(piel con-escamas)
(sangre-temp fria)
=>
(printout t “Es un reptil“ crlf)
(assert(animal reptil))
)

(defrule leer-movimiento
(declare (salience 1))
(not (animal ?))
=>
(printout t “Indique como se mueve (andando, volando)“ crlf)
(assert (movimiento (read)))
)

(defrule mamifero
(declare (salience 0))
(piel con-pelo)
(sangre-temp caliente)
(movimiento andando)
=>
(printout t “Es un mamifero“ crlf)
(assert(animal mamifero))
)

(defrule ave
(declare (salience 0))
(piel con-plumas)
(sangre-temp caliente)
(movimiento volando)
=>
(printout t “Es un ave“ crlf)
(assert(animal ave))
)

(defrule murcielago
(declare (salience 0))
(piel con-pelo)
(sangre-temp caliente)
(movimiento volando)
=>
(printout t “Es un murcielago“ crlf)
(assert(animal mamifero))
)

(defrule avestruz
(declare (salience 0))
(piel con-plumas)
(sangre-temp caliente)
(movimiento andando)
=>
(printout t “Es una avestruz“ crlf)
(assert(animal ave))
)

(defrule ninguno
(declare (salience -2))
(not (animal ?))
=>
(printout t “Categoria desconocida“ crlf)
)