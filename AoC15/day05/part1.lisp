(defun check-for-double-char (word)
  (when word (if (< 0 (reduce #'+ (loop for letter across word
        when (search (coerce (list letter letter) 'string) word) collect 1)))
    word)))

(defun contains-3-vowels (word)
  (when word (if (< 2 (reduce #'+ (loop for letter across word
        when (find letter "AEIOU") collect 1)))
    word)))

(defun check-for-forbiden (word)
  (when word (if (< 0 (reduce #'+ (loop for forbiden across #("AB" "CD" "PQ" "XY")
        when (search forbiden word) collect 1)))
    nil
    word)))

(defun main ()
  (let ((strings
          (loop for str = (read *standard-input* nil nil)
                while str
                when str collect (string str))))
  (write (length (remove nil
    (mapcar 'contains-3-vowels
      (mapcar 'check-for-double-char
        (mapcar 'check-for-forbiden strings))))))))
