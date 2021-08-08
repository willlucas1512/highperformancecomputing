program main
    implicit none
    integer, parameter :: nMaximo = 16000
    double precision, dimension (nMaximo,nMaximo) :: A
    double precision, dimension (nMaximo) :: x
    double precision, dimension (nMaximo) :: b

    double precision :: s,t, start_ij,end_ij, start_ji,end_ji
    integer :: i,j,n,k

    call RANDOM_SEED()    
    call random_number(A)
    call random_number(x)

    open(unit=1, file="temposFortran.csv", status="unknown", action="write")
    write(1,"(a)") "n,TempoIJ,TempoJI"
    
    do k=0, 16
        n = k * 1000

        call cpu_time(start_ij)
        do i=1, n
            s = 0
            do j=1, n
                s = s + A(i,j) * x(j)
            end do
            b(i) = s
        end do
        call cpu_time(end_ij)

        b(:n) = 0 
        
        call cpu_time(start_ji)
        do j=1, n
            t = x(j)
            do i=1, n
                b(i) = b(i) + A(i,j) * t
            end do
        end do
        call cpu_time(end_ji)
        
        write(*,*) n,(end_ij-start_ij),(end_ji-start_ji) 
        write(1,*) n,",",(end_ij-start_ij),",",(end_ji-start_ji) 
    end do

    close(unit=1)

end program main
