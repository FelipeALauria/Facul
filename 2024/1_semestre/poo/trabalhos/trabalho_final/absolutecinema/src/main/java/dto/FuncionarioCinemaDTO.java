package DTO;

/**
 *
 * @author felip
 */
public class FuncionarioCinemaDTO extends FuncionarioDTO {

    private String faxina;
    private static String classificacao = "Cinema";
    /**
     * @return the faxina
     */
    public String getFaxina() {
        return faxina;
    }

    /**
     * @param faxina the faxina to set
     */
    public void setFaxina(String faxina) {
        this.faxina = faxina;
    }
}
