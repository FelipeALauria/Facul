package DTO;

/**
 *
 * @author felip
 */
public class FuncionarioBomboniereDTO extends FuncionarioDTO {

    private double meta;
    private static String classificacao = "Bomboniere";

    /**
     * @return the meta
     */
    public double getMeta() {
        return meta;
    }

    /**
     * @param meta the meta to set
     */
    public void setMeta(double meta) {
        this.meta = meta;
    }

}
