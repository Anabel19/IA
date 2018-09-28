(defglobal ?*n* = (random 1 100))

(deffunction guess (?number)
   (if (> ?number ?*n*)
      then
      (printout t ?number "es mayor al numero almacenado")
    else
      (if (< ?number ?*n*)
         then
         (printout t ?number "es menor al numero almacenado")

(defrule new
   ?f <- (new)
   =>
   (retract ?f)
   (printout t "Write number 1 && 100: ")
   (assert (number (read)))
   (guess number))

