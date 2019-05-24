    program produto
        use omp_lib
        implicit none

        ! Para executar em Linux:
        ! gfortran produto_fortran.f95 -o produto_f -mcmodel=large -fopenmp
        ! ./produto_f 

        ! Determinar a quantidade de linhas e colunas na linha abaixo antes de compilar o código
        integer, parameter :: num_linhas = 2000, num_colunas = 2000
        real*8 :: matriz(num_linhas,num_colunas), vetor(num_linhas), resultado(num_linhas)

        call produto_mv(matriz, vetor, resultado, num_linhas, num_colunas)

	end program produto

    subroutine preencher_vetor(vetor, n)
        integer n
        real*8 vetor(n)
        real(kind=8) :: r

!$omp parallel do num_threads(4) private(i) shared(vetor)
        do i=1, n
            call random_number(r)
            vetor(i) = r
        end do
!$omp end parallel do

    end subroutine

    subroutine preencher_matriz(matriz, m, n)
        integer m, n
        real*8 matriz(m,n)
        real(kind=8) :: r

!$omp parallel do num_threads(4) private(i,j) shared(matriz)
        do i = 1, m
            do j = 1, n
                call random_number(r)
                matriz(i,j) = r
            end do
        end do
!$omp end parallel do

    end subroutine

    subroutine zerar_resultados(vetor, n)
        integer n
        real*8 vetor(n)
        do i=1, n
            vetor(i) = 0
        end do
    end subroutine

    subroutine produto_mv(matriz, vetor, resultado, n, m)
        integer n, m
        real*8 matriz(n,m), vetor(n), resultado(n), start, end, t

        call cpu_time(start)
        call preencher_matriz(matriz,n,m)
        call cpu_time(end)

        t = end - start
        print *, "Tempo de criacao da matriz aleatoria:", t        

        call cpu_time(start)
        call preencher_vetor(vetor,n)
        call cpu_time(end)

        t = end - start
        print *, "Tempo de criacao do vetor aleatorio:", t 


        call zerar_resultados(resultado,n)
        call cpu_time(start)

!$omp parallel do num_threads(4) private(i,j) shared(resultado)        
        do i = 1, n
            do j = 1, m
                resultado(i) = resultado(i) + matriz(i, j)*vetor(j)
            end do
        end do
!$omp end parallel do

        call cpu_time(end)

        t = end - start
        print *, "Tempo de execucao, em segundos, para linha:", t

        call zerar_resultados(resultado,n)

        call cpu_time(start)

!$omp parallel do num_threads(4) private(i,j) shared(resultado)        
        do j = 1, m
            do i = 1, n
                resultado(i) = resultado(i) + matriz(i, j)*vetor(j)
            end do
        end do
!$omp end parallel do

        call cpu_time(end)

        t = end - start
        print *, "Tempo de execucao, em segundos, para coluna:", t
    end subroutine