(defun direction-to-operator (direction)
  "Parse direction instruction to an operator"
  (cond ((equal direction #\<) (list -1  0))
        ((equal direction #\>) (list  1  0))
        ((equal direction #\^) (list  0  1))
        ((equal direction #\v) (list  0 -1))))

(defun execute-path (start operators)
  "Recursively execute the path using operators"
  (append (list start) (when operators
    (let ((operator (pop operators)))
      (execute-path (mapcar #'+ start operator) operators)))))

(defun main ()
  (let ((operators
    (remove nil
      (loop for direction = (read-char *standard-input* nil nil)
            while direction
            collect (direction-to-operator direction)))))
    (write (length (remove-duplicates
                (execute-path (list 0 0) operators) :test #'equal)))))
