module com.absolutecinema {
    requires javafx.controls;
    requires javafx.fxml;
    requires java.sql;
    requires java.base;

    opens com.absolutecinema to javafx.fxml;
    opens DTO to javafx.base;

    exports com.absolutecinema;
}
