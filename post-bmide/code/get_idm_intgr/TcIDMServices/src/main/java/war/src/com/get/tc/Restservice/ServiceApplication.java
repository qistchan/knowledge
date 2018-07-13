
package war.src.com.get.tc.Restservice;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.builder.SpringApplicationBuilder;
import org.springframework.boot.context.web.SpringBootServletInitializer;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.ImportResource;
import org.springframework.context.annotation.PropertySource;

@SpringBootApplication
@ImportResource(value = "classpath:beans.xml")
@PropertySource({"classpath:application.properties"})
@ComponentScan("com.get.tc.soa.service.GETIDMServices")
public class ServiceApplication extends SpringBootServletInitializer
{
    private static Class<ServiceApplication> applicationClass = ServiceApplication.class;

	public static void main(String[] args)
	{
		SpringApplication.run(ServiceApplication.class, args);
	}

	@Override
    protected SpringApplicationBuilder configure(SpringApplicationBuilder application)
	{
        return application.sources(applicationClass);
    }
}
