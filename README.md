# progetto_SO 2020/2021
progetto per il corso di sistemi operativi 2020/2021
 
Lorenzo Di Filippo 1837562 

tutti i codici scritti si trovano nella seguente directory:
/progetto_SO/sistemi_operativi_2019_20-master/source/08_disastrOStrOS_04_resources

i file scritti sono:
     
    nel test1 si avviano 10 processi di cui 1 solo scrive (45 char) mentre gli altri
    leggono ciascuno 5 char
        -test1

    nel test2 si avviano 10 processi di cui 2 scrivono ciscuno 20 char ma su due 
    distinte, mentre gli altri 8 processi leggono 5 char ciascuno (4 da una coda
    e 4 dall'altra)
        -test2

    nel test3 si avviano 2 processi di cui uno scrive 20 char ma a blocchi di 4 per volta
    mentre il secondo processo legge 5 char ad ogni iterazione (se ci sono meno di 5 char 
    nella coda il processo legge quelli e aspetta che il primo processo scriva nuovamente)
        -test3
    
    file contenenti le strutture per rappresentare le code e le funzioni base 
        -strutture.h
        -strutture.c

    foglio in cui si può reindirizzare l'output quando questo è troppo lungo per
    il terminale di linux
        -test.txt

    file contente la definizione della routine che si deve eseguire quando viene 
    chiamta la systemcall  leggi_coda_systemcall
        -leggi.c

    file contente la definizione della routine che si deve eseguire quando viene 
    chiamta la systemcall  scrivi_coda_systemcall
        -scrivi.c
    

i file che si sono modificati sono:

    all'interno di tutti i file che si sono modificati sono stati inseriti dei
    commenti per distinguere il codice modificato da quello che era già presente

        -disastOS.c
        -disastrOS.h
        -disastrOS_constants.h
        -disastrOS_syscalls.h
        -disastrOS_test.c   


