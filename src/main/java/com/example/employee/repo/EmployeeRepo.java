package com.example.employee.repo;

import com.example.employee.modell.Employee;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.stereotype.Repository;

import java.util.List;

@Repository
public interface EmployeeRepo extends JpaRepository<Employee,Long> {
    //@Query("select s from Employees where name like %%")
    //Page<Employee> findById(Pageable pageable);
}
