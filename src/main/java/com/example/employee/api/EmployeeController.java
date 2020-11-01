package com.example.employee.api;


import com.example.employee.exceptions.ResourceNotFoundException;
import com.example.employee.modell.Employee;
import com.example.employee.repo.EmployeeRepo;
import com.example.employee.service.EmployeeService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.PageRequest;
import org.springframework.data.domain.Pageable;
import org.springframework.data.domain.Sort;
import org.springframework.http.HttpHeaders;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;


import java.util.List;
import java.util.Map;
import java.util.Optional;


@RestController
@RequestMapping("api/v1/employees")
public class EmployeeController {

    @Autowired
    private EmployeeService employeeService;

    @Autowired
    private EmployeeRepo repo;

    @GetMapping
        public ResponseEntity<List<Employee>> getAllEmp(){
        Page<Employee> employees = employeeService.getAllEmp();
        List<Employee> employeesList = employees.getContent();
        return new ResponseEntity<>(employeesList, HttpStatus.OK);

    }

    @GetMapping("/{id}")
    public ResponseEntity<Employee> getEmployeeById(@PathVariable(value = "id")long employeeId)
            throws ResourceNotFoundException {
        return new ResponseEntity<>(employeeService.getEmployeeById(employeeId),HttpStatus.OK);
    }

    @PostMapping
    public ResponseEntity<Employee> createEmployee(@RequestBody Employee employee)
    {
        return new ResponseEntity<>(employeeService.createEmployee(employee), HttpStatus.CREATED);
    }

    @PutMapping("/{id}")
    public ResponseEntity<Employee> updateEmployee(@PathVariable(value = "id")Long employeeId,
                                                   @RequestBody Employee employeeDetails)
            throws ResourceNotFoundException {
        return ResponseEntity.ok().body(this.employeeService.updateEmployee(employeeId, employeeDetails));
    }

    @DeleteMapping("/{id}")
    public ResponseEntity<Void> deleteEmployee(@PathVariable(value = "id")Long employeeId)
            throws ResourceNotFoundException{

         employeeService.deleteEmployee(employeeId);
        return new ResponseEntity<Void>(HttpStatus.OK);

    }

    @GetMapping("/page")
    public Page<Employee> findMe(){
        //Pageable pageable = PageRequest.of(0, 66, Sort.by(Sort.Order.asc("id")));
        return repo.findAll(PageRequest.of(0, 66, Sort.by(Sort.Order.asc("id"))));
    }


}