package com.example.employee.service;

import com.example.employee.exceptions.ResourceNotFoundException;
import com.example.employee.modell.Employee;
import com.example.employee.repo.EmployeeRepo;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.PageRequest;
import org.springframework.data.domain.Sort;
import org.springframework.stereotype.Component;
import org.springframework.stereotype.Service;



@Component
@Service
public class EmployeeService implements IEmployeeService {

    @Autowired
    private EmployeeRepo employeeRepo;

    @Override
    public Page<Employee> getAllEmp() {
        return employeeRepo.findAll(PageRequest.of(0, Integer.MAX_VALUE, Sort.by(Sort.Order.asc("id"))));
    }



    @Override
    public Employee getEmployeeById(Long id) throws ResourceNotFoundException {
         return employeeRepo.findById(id).orElseThrow( () -> new ResourceNotFoundException
                 ("Employee not found for this ID: " + id));
    }

    @Override
    public Employee createEmployee(Employee employee) {
        return employeeRepo.save(employee);
    }


    // orElseThrow is a lambda function () -> new EXCEPTION()
    @Override
    public Employee updateEmployee(Long id, Employee employee) throws ResourceNotFoundException{
            Employee updatedEmployee = employeeRepo.findById(id).orElseThrow( () -> new ResourceNotFoundException
                    ("Employee not found for" + "this ID: "+employee.getId()) );


        updatedEmployee.setFirstname(employee.getFirstname());
        updatedEmployee.setLastname(employee.getLastname());
        updatedEmployee.setAge(employee.getAge());
        updatedEmployee.setEntrance(employee.getEntrance());
        updatedEmployee.setBirth(employee.getBirth());
        updatedEmployee.setSalary(employee.getSalary());
        updatedEmployee.setGender(employee.getGender());

        return employeeRepo.save(updatedEmployee);
    }

    @Override
    public void deleteEmployee(Long id) throws ResourceNotFoundException {
        Employee deletedEmployee = employeeRepo.findById(id).orElseThrow(() -> new ResourceNotFoundException
                ("Employee not found for this ID: " + id));
        employeeRepo.delete(deletedEmployee);
    }



}
