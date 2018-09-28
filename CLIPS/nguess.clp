;(defglobal ?*n* = (random 1 100))
(defglobal ?*n* = 39)

(deffunction guess (?number)
   (if (> ?number ?*n*)  then
      (printout t ?number " es mayor al numero almacenado" crlf)
	  (assert (new))
    else
      (if (< ?number ?*n*)  then
         (printout t ?number " es menor al numero almacenado" crlf)
		 (assert (new)))
	else 
	  (if (= ?number ?*n*)	then
		(printout t "ready! is the number" crlf)))
)

(defrule initGuess
	=>
	(assert (new)))
	
(defrule new
   ?f <- (new)
   =>
   (retract ?f)
   (printout t "Write number 1 && 100: ")
   (bind ?answer (read))
   (guess ?answer))

