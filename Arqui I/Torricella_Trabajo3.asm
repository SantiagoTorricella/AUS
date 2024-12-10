.data
# Punteros para listas
slist:      .word 0          # Lista simple de nodos liberados
cclist:     .word 0          # Lista de categorías
wclist:     .word 0          # Categoría en curso seleccionada
schedv:     .space 32        # Vector de funciones del menú

# Mensajes para el menú y errores
menu:       .ascii "Colecciones de objetos categorizados\n"
            .ascii "====================================\n"
            .ascii "1-Nueva categoria\n"
            .ascii "2-Siguiente categoria\n"
            .ascii "3-Categoria anterior\n"
            .ascii "4-Listar categorias\n"
            .ascii "5-Borrar categoria actual\n"
            .ascii "6-Anexar objeto a la categoria actual\n"
            .ascii "7-Listar objetos de la categoria\n"
            .ascii "8-Borrar objeto de la categoria\n"
            .ascii "0-Salir\n"
            .asciiz "Ingrese la opcion deseada: "

error:      .asciiz "Error: "
success:    .asciiz "La operación se realizo con exito\n\n"
catName:    .asciiz "\nIngrese el nombre de una categoria: "
selCat:     .asciiz "\nSe ha seleccionado la categoria:"
idObj:      .asciiz "\nIngrese el ID del objeto a eliminar: "
objName:    .asciiz "\nIngrese el nombre de un objeto: "
succes:	    .asciiz "La operacion se realizo con exito \n\n"

.text
main:
    # Inicialización del vector de funciones (schedv)
    la      $t0, schedv
    la      $t1, newcategory      # 1-Nueva categoria
    sw      $t1, 0($t0)
    la      $t1, nextcategory     # 2-Siguiente categoria
    sw      $t1, 4($t0)
    la      $t1, prevcategory     # 3-Categoria anterior
    sw      $t1, 8($t0)
    la      $t1, listcategories   # 4-Listar categorias
    sw      $t1, 12($t0)
    la      $t1, delcategory      # 5-Borrar categoria actual
    sw      $t1, 16($t0)
    la      $t1, newobject        # 6-Anexar objeto
    sw      $t1, 20($t0)
    la      $t1, listobjects      # 7-Listar objetos
    sw      $t1, 24($t0)
    la      $t1, delobject        # 8-Borrar objeto
    sw      $t1, 28($t0)

menu_loop:
    # Imprimir el menú
    la      $a0, menu
    li      $v0, 4               # syscall: print_string
    syscall

    # Leer opción del usuario
    li      $v0, 5               # syscall: read_int
    syscall
    move    $t0, $v0             # Guardar opción en $t0

    # Validar si la opción es válida (0-8)
    bltz    $t0, invalid_option
    li      $t1, 8
    bgt     $t0, $t1, invalid_option

    # Ejecutar la función correspondiente desde schedv
    la      $t1, schedv
    mul     $t0, $t0, 4          # Desplazamiento: opción * 4 bytes
    lw      $t2, 0($t1)          # Dirección de la función
    jalr    $t2                  # Llamar función
    j       menu_loop

invalid_option:
    # Manejo de error para opción inválida
    la      $a0, error
    li      $v0, 4               # syscall: print_string
    syscall

    li      $v0, 1
    li      $a0, 101             # Código de error (101)
    syscall
    j       menu_loop
    
newcategory:
    # Guardar $ra en la pila
    addiu   $sp, $sp, -4
    sw      $ra, 4($sp)

    # Solicitar al usuario un nombre para la categoría
    la      $a0, catName          # Mensaje: "Ingrese el nombre de una categoría:"
    jal     getblock              # Llama a getblock para obtener el string
    move    $a2, $v0              # Guarda la dirección del bloque en $a2

    # Añadir la nueva categoría a la lista circular
    la      $a0, cclist           # Dirección de la lista de categorías
    li      $a1, 0                # $a1 = NULL, ya que no tiene lista de objetos asociada
    jal     addnode               # Llama a addnode para agregar el nodo
    move    $t0, $v0              # Dirección del nodo creado

    # Si la lista de categorías estaba vacía, actualizar `wclist`
    lw      $t1, wclist
    bnez    $t1, newcategory_end  # Si `wclist` no es NULL, saltar
    sw      $t0, wclist           # Si estaba vacía, actualizar `wclist` con el nuevo nodo

newcategory_end:
    # Preparar el retorno exitoso
    li      $v0, 0                # Código de éxito: 0
    lw      $ra, 4($sp)           # Restaurar $ra
    addiu   $sp, $sp, 4           # Restaurar la pila
    jr      $ra                   # Retornar

getblock:
    addi    $sp, $sp, -4
    sw      $ra, 4($sp)

    # Imprimir mensaje
    li      $v0, 4
    syscall

    # Reservar memoria para el string
    jal     smalloc
    move    $a0, $v0              # Dirección del bloque reservado
    li      $a1, 16               # Tamaño máximo del string
    li      $v0, 8                # syscall: read_string
    syscall
    move    $v0, $a0              # Retornar la dirección del bloque

    lw      $ra, 4($sp)
    addi    $sp, $sp, 4
    jr      $ra
addnode:
    addi    $sp, $sp, -8
    sw      $ra, 8($sp)
    sw      $a0, 4($sp)

    jal     smalloc               # Reservar memoria para un nuevo nodo
    sw      $a1, 4($v0)           # Guardar el contenido en el nodo
    sw      $a2, 8($v0)           # Guardar el nombre de la categoría

    # Obtener el primer nodo
    lw      $t0, ($a0)
    beqz    $t0, addnode_empty_list

    # Añadir al final de la lista
    lw      $t1, 0($t0)           # Último nodo
    sw      $t1, 0($v0)           # Actualizar puntero prev
    sw      $t0, 12($v0)          # Actualizar puntero next
    sw      $v0, 12($t1)          # Actualizar siguiente del último nodo
    sw      $v0, 0($t0)           # Actualizar anterior del primero
    j       addnode_exit

addnode_empty_list:
    sw      $v0, ($a0)            # Actualizar lista para apuntar al nuevo nodo
    sw      $v0, 0($v0)           # Nodo apunta a sí mismo (prev)
    sw      $v0, 12($v0)          # Nodo apunta a sí mismo (next)
    
addnode_exit:
    lw      $ra, 8($sp)
    addi    $sp, $sp, 8
    jr      $ra
delnode:
	addi $sp, $sp , -8
	sw $ra  , 8($sp)
	sw $a0, 4($sp)
	lw $a0, 8($a0)
	jal sfree
	lw $a0, 4($sp)
	lw $t0, 12($a0)
node:
	beq $a0, $t0, delnode_point_self
	lw $t1, 0($a0)
	sw $t1, 0($t0)
	sw $t0, 12($t1)
	lw $t1, 0($a1)
again:
	bne $a0, $t1, delnode_exit
	sw $t0, ($a1)
	j delnode_exit
delnode_point_self:
	sw $zero , ($a1)
delnode_exit:
	jal free
	lw $ra, 8($sp)
	addi $sp, $sp, 8
	jr $ra 

	
listcategories:
    # Guardar $ra en la pila
    addiu   $sp, $sp, -4
    sw      $ra, 4($sp)

    # Verificar si la lista de categorías está vacía
    lw      $t0, cclist           # $t0 apunta al primer nodo de categorías
    beqz    $t0, no_categories    # Si es NULL, no hay categorías

    # Imprimir mensaje de categorías
    la      $a0, menu             # Encabezado del menú
    li      $v0, 4                # syscall: print_string
    syscall

    # Iniciar recorrido por la lista circular
    move    $t1, $t0              # $t1 = puntero al nodo actual
    listcategories_loop:
    # Cargar nombre de la categoría desde el nodo
    lw      $a0, 8($t1)           # Dirección del nombre (campo del nodo)
    lw      $t2, wclist           # Cargar la categoría seleccionada
    li      $v0, 4                # syscall: print_string
    syscall

    # Mostrar ">" si es la categoría seleccionada
    beq     $t1, $t2, show_selected
    j       continue_loop

    show_selected:
    la      $a0, " >"             # Mostrar " >"
    li      $v0, 4                # syscall: print_string
    syscall

    continue_loop:
    # Avanzar al siguiente nodo
    lw      $t1, 12($t1)          # $t1 = puntero al siguiente nodo
    bne     $t1, $t0, listcategories_loop # Repetir hasta regresar al primer nodo

    # Retornar éxito
    li      $v0, 0                # Código de éxito
    lw      $ra, 4($sp)           # Restaurar $ra
    addiu   $sp, $sp, 4           # Restaurar la pila
    jr      $ra                   # Retornar

    no_categories:
    # Manejar el error (301) si no hay categorías
    la      $a0, error            # Imprimir "Error: "
    li      $v0, 4                # syscall: print_string
    syscall

    li      $a0, 301              # Código de error
    li      $v0, 1                # syscall: print_int
    syscall

    # Preparar para salir
    li      $v0, 301              # Código de error de retorno
    lw      $ra, 4($sp)           # Restaurar $ra
    addiu   $sp, $sp, 4           # Restaurar la pila
    jr      $ra                   # Retornar

    delcategory:
    # Guardar $ra en la pila
    addiu   $sp, $sp, -4
    sw      $ra, 4($sp)

    # Verificar si hay categorías
    lw      $t0, wclist           # Cargar la categoría seleccionada
    beqz    $t0, no_categories    # Si es NULL, no hay categorías

    # Verificar si la lista de objetos está vacía
    lw      $t1, 4($t0)           # Cargar puntero a la lista de objetos
    beqz    $t1, delete_category  # Si está vacía, proceder a borrar categoría

    # Borrar los objetos relacionados
delete_objects:
    lw      $t2, ($t1)            # Dirección del primer nodo de la lista de objetos
    beqz    $t2, delete_category  # Si no hay objetos, continuar con categoría
delete_objects_loop:
    jal     delnode               # Eliminar nodo de la lista de objetos
    lw      $t2, ($t1)            # Cargar siguiente nodo
    bnez    $t2, delete_objects_loop # Repetir hasta vaciar la lista

    # Borrar la categoría seleccionada
delete_category:
    lw      $t3, 12($t0)          # Dirección de la siguiente categoría
    beq     $t0, $t3, only_node   # Si apunta a sí misma, es el único nodo
    lw      $t4, 0($t0)           # Dirección de la categoría anterior
    sw      $t4, 0($t3)           # Actualizar puntero prev de la siguiente categoría
    sw      $t3, 12($t4)          # Actualizar puntero next de la categoría anterior
    lw      $t1, cclist           # Verificar si es el nodo principal
    bne     $t0, $t1, update_wclist
    sw      $t3, cclist           # Actualizar cclist si se borra el nodo principal
update_wclist:
    lw      $t1, 12($t0)          # Apuntar wclist a la siguiente categoría
    sw      $t1, wclist
    j       free_category

only_node:
    sw      $zero, cclist         # Vaciar lista de categorías
    sw      $zero, wclist

free_category:
    jal     delnode               # Liberar la memoria del nodo de categoría

    # Operación exitosa
    la      $a0, success
    li      $v0, 4                # syscall: print_string
    syscall
    j       delcategory_exit



delcategory_exit:
    lw      $ra, 4($sp)           # Restaurar $ra
    addiu   $sp, $sp, 4           # Restaurar la pila
    jr      $ra                   # Retornar
    newobject:
    # Guardar $ra en la pila
    addiu   $sp, $sp, -4
    sw      $ra, 4($sp)

    # Verificar si hay categorías seleccionadas
    lw      $t0, wclist           # Cargar categoría seleccionada
    beqz    $t0, no_category      # Si es NULL, error (501)

    # Obtener la lista de objetos de la categoría
    lw      $t1, 4($t0)           # $t1 = puntero a la lista de objetos
    beqz    $t1, empty_object_list # Si es NULL, la lista está vacía

    # Encontrar el último nodo para calcular el nuevo ID
    lw      $t2, ($t1)            # Cargar el primer nodo de objetos
find_last_object:
    lw      $t3, 12($t2)          # Cargar el siguiente nodo
    beq     $t2, $t3, last_object # Si es circular y apunta a sí mismo, es el último
    bne     $t3, $t2, find_last_object # Repetir hasta encontrar el último nodo

last_object:
    lw      $t4, 8($t2)           # Cargar el ID del último nodo
    addi    $t4, $t4, 1           # ID del nuevo objeto = último ID + 1
    j       create_object

empty_object_list:
    li      $t4, 1                # ID del nuevo objeto = 1

create_object:
    # Solicitar el nombre del objeto
    la      $a0, objName          # Mensaje: "Ingrese el nombre de un objeto:"
    jal     getblock              # Llama a getblock para obtener el string
    move    $a2, $v0              # Guarda la dirección del bloque en $a2

    # Añadir el nuevo objeto a la lista de objetos
    move    $a0, $t1              # Dirección de la lista de objetos
    move    $a1, $t4              # Nuevo ID como contenido del nodo
    jal     addnode               # Llama a addnode para añadir el nodo
    sw      $v0, 4($t0)           # Actualizar puntero a la lista en la categoría

    # Operación exitosa
    la      $a0, success          # Mensaje: "La operación se realizó con éxito"
    li      $v0, 4                # syscall: print_string
    syscall
    j       newobject_exit

no_category:
    # Manejar error (501) si no hay categorías seleccionadas
    la      $a0, error            # Mensaje: "Error: "
    li      $v0, 4                # syscall: print_string
    syscall

    li      $a0, 501              # Código de error
    li      $v0, 1                # syscall: print_int
    syscall

newobject_exit:
    lw      $ra, 4($sp)           # Restaurar $ra
    addiu   $sp, $sp, 4           # Restaurar la pila
    jr      $ra                   # Retornar
    listobjects:
    # Guardar $ra en la pila
    addiu   $sp, $sp, -4
    sw      $ra, 4($sp)

    # Verificar si hay categorías seleccionadas
    lw      $t0, wclist           # Cargar categoría seleccionada
    beqz    $t0, no_categories    # Si es NULL, error (601)

    # Verificar si la lista de objetos está vacía
    lw      $t1, 4($t0)           # $t1 = puntero a la lista de objetos
    beqz    $t1, no_objects       # Si es NULL, error (602)

    # Recorrer y listar los objetos
    lw      $t2, ($t1)            # Cargar el primer nodo de objetos
listobjects_loop:
    # Imprimir el ID del objeto
    lw      $a0, 8($t2)           # Cargar el ID del objeto
    li      $v0, 1                # syscall: print_int
    syscall

    # Imprimir separador " - "
    la      $a0, " - "
    li      $v0, 4                # syscall: print_string
    syscall

    # Imprimir el nombre del objeto
    lw      $a0, 4($t2)           # Cargar el nombre (bloque asociado)
    li      $v0, 4                # syscall: print_string
    syscall

    # Imprimir un salto de línea
    la      $a0, return
    li      $v0, 4                # syscall: print_string
    syscall

    # Avanzar al siguiente nodo
    lw      $t2, 12($t2)          # $t2 = puntero al siguiente nodo
    bne     $t2, ($t1), listobjects_loop # Repetir hasta regresar al primer nodo

    # Finalizar con éxito
    la      $a0, success          # Mensaje de éxito
    li      $v0, 4                # syscall: print_string
    syscall
    j       listobjects_exit


no_objects:
    # Manejar error (602) si no hay objetos en la categoría seleccionada
    la      $a0, error            # "Error: "
    li      $v0, 4                # syscall: print_string
    syscall

    li      $a0, 602              # Código de error
    li      $v0, 1                # syscall: print_int
    syscall

listobjects_exit:
    lw      $ra, 4($sp)           # Restaurar $ra
    addiu   $sp, $sp, 4           # Restaurar la pila
    jr      $ra                   # Retornar

delobject:
    # Guardar $ra en la pila
    addiu   $sp, $sp, -4
    sw      $ra, 4($sp)

    # Verificar si hay categorías seleccionadas
    lw      $t0, wclist           # Cargar categoría seleccionada
    beqz    $t0, no_categories    # Si es NULL, error (701)

    # Verificar si la lista de objetos está vacía
    lw      $t1, 4($t0)           # $t1 = puntero a la lista de objetos
    beqz    $t1, not_found        # Si está vacía, el ID no existe

    # Solicitar el ID del objeto a borrar
    la      $a0, idObj            # Mensaje: "Ingrese el ID del objeto a eliminar:"
    li      $v0, 4                # syscall: print_string
    syscall

    li      $v0, 5                # syscall: read_int
    syscall
    move    $t2, $v0              # $t2 = ID ingresado

    # Buscar el objeto en la lista
    lw      $t3, ($t1)            # Cargar el primer nodo de objetos
find_object_loop:
    lw      $t4, 8($t3)           # Cargar el ID del nodo actual
    beq     $t4, $t2, delete_object # Si coincide, borrar el nodo

    # Avanzar al siguiente nodo
    lw      $t3, 12($t3)          # $t3 = puntero al siguiente nodo
    bne     $t3, ($t1), find_object_loop # Repetir hasta regresar al primer nodo

    # Si no se encontró el ID, mostrar notFound
not_found:
    la      $a0, "notFound\n"     # Mensaje: "notFound"
    li      $v0, 4                # syscall: print_string
    syscall
    j       delobject_exit

delete_object:
    # Llamar a delnode para liberar el nodo
    move    $a0, $t3              # Dirección del nodo a borrar
    move    $a1, $t1              # Dirección de la lista de objetos
    jal     delnode               # Liberar memoria

    # Operación exitosa
    la      $a0, success          # Mensaje de éxito
    li      $v0, 4                # syscall: print_string
    syscall
    j       delobject_exit


    syscall

delobject_exit:
    lw      $ra, 4($sp)           # Restaurar $ra
    addiu   $sp, $sp, 4           # Restaurar la pila
    jr      $ra                   # Retornar
