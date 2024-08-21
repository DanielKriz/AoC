;; Collection of simple functions that are used thorough the days of AoC

;; Basically stolen from https://lispcookbook.github.io/cl-cookbook/strings.html
(defun split-by-delimeter (string delimeter)
  "Splits 'string' by delimeter and returns it as a string"
  (loop for i = 0 then (1+ j)
        as j = (position delimeter string :start i)
        collect (subseq string i j)
        while j))

(defun smallest (list)
  "Returns smallest element of the list"
  (apply 'min list))

(defun left-rotate (l)
  "Rotates list given by 'l' one element to the right"
  (append (cdr l) (cons (car l) ())))

(defun collect-on-even (l)
  "Collect all items on even positions in list 'l'"
  (loop for (a b) on l by #'cddr
        when b collect b))

(defun collect-on-odd (l)
  "Collect all items on odd positions in list 'l'"
  (loop for (a b) on l by #'cddr
        when a collect a))

