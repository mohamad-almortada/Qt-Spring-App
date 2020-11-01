package com.example.employee.service;

import com.example.employee.exceptions.ResourceNotFoundException;
import com.example.employee.modell.Employee;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;

import java.util.List;



public interface IEmployeeService {
    Page<Employee> getAllEmp();
    Employee getEmployeeById(Long id) throws ResourceNotFoundException;
    Employee createEmployee(Employee employee);
    Employee updateEmployee(Long id, Employee employee) throws ResourceNotFoundException;
    void deleteEmployee(Long id) throws ResourceNotFoundException;
    //Page<Employee> findMe(String name, Pageable pageable);
}
