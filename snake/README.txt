﻿Автор: Безъязычный Семён
Сроки выполнения: 1-8 марта 
На C++ реализовать игру Snake, состоит из блоков model, view, controller
при достижение границы поля или собственного хвоста игра заканчивается
змейка изначально в одну клетку, занимает случайное  положение на выделенном участке поля и движется в случайном направлении
через каждые t единиц времени на поле в случайном месте появляется объект типа “пища”
попадая в это положение змейка увеличивает свою длину на 1
при нажатии на стрелки клавиатуры змейка меняет направление движения в указанную сторону: вниз, вверх, влево, вправо
каждые t1 единиц времени происходит перерисовка поля, проверка условия окончания игры, проверка на “пищу”
поле кодируется в виде матрицы размера nxn
“пища” занимает случайное положение в этой матрице, если это не '0', кодируется ‘2’ 
каждый элемент змейки в своей ячейке матрицы, кодируется ‘1’
все остальные ячейке кодируются ‘0’
условия окончания игры: в очередной ячейке ‘-1’ || ‘1’
если в ячейке ‘2’, то смотрим, что выдал controller, идём в нужную сторону, при этом хвост не меняет своё положение, добавляем ‘1’  в эту ячейку (увеличили длину)
ячейки, которые проходит змейка, заполняются ‘0’
есть динамически расширяемый массив с координатами змейки: первая ячейка tail, последняя head
если не “пища”, то сдвигаем массив влево на одну позицию, в head заносим новые координаты
если “пища”, то увеличиваем размер массива, head сдвигаем на один, заносим новые координаты

 
