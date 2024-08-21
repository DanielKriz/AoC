(defun move-story (story operator)
  (if (equal operator #\( )
    (+ story 1)
    (- story 1)))

(defun return-idx-of-basement (story idx plan)
  (if (< story 0)
    idx
    (return-idx-of-basement (move-story story (char plan 0)) (+ idx 1)  (subseq plan 1))))

(defun main ()
 (write (return-idx-of-basement 0 0 (read-line))))
