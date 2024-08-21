(defun move-story (story operator)
  (if (equal operator #\( )
    (+ story 1)
    (- story 1)))

(defun execute-plan (story plan)
  (if (equal plan "")
   story
   (execute-plan (move-story story (char plan 0)) (subseq plan 1))))

(defun main ()
 (write (execute-plan 0 (read-line))))
