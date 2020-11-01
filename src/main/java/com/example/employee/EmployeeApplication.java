package com.example.employee;

import com.example.employee.modell.Employee;
import com.example.employee.repo.EmployeeRepo;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.context.properties.EnableConfigurationProperties;
import org.springframework.context.ConfigurableApplicationContext;

@SpringBootApplication
public class EmployeeApplication {

	public static void main(String[] args) {


		SpringApplication.run(EmployeeApplication.class, args);


	}


}
