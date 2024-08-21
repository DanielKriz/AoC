(load "part1.lisp")

(defun main ()
  (let ((operators
    (remove nil
      (loop for direction = (read-char *standard-input* nil nil)
            while direction
            collect (direction-to-operator direction)))))
    (let ((santa-operators (collect-on-odd operators)))
    (let ((robot-operators (collect-on-even operators)))
      (write (length (remove-duplicates
               (append
                 (execute-path (list 0 0) santa-operators)
                 (execute-path (list 0 0) robot-operators))
               :test #'equal)))))))
