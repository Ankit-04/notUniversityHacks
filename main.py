def main():
    answer_to_letter = {
        'a\n':1,
        'b\n':2,
        'c\n':3,
        'd\n':4,
        'e\n':5
    }
    try:
        f = open("questions.txt","r")
        content = f.readlines()
        number_of_questions = int(content[1])
        
        for i in range(number_of_questions):
            
            question_title = content[i*5 + 3 ]
            question_options = content[i*5 + 5].split(' ')
            question_answer = answer_to_letter.get(str(content[i*5 + 6]),)
            
            print(question_title,question_options, question_answer)
            
        
    finally:
        f.close()



if __name__ == '__main__':
    main()