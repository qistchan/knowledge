package com.get.ontrack.getrans.clientx;

public class ResponseVo {
    
    private boolean status;
    private String message;
    
    public ResponseVo(){}

    public boolean isSuccess() {
        return status;
    }

    public void setStatus(boolean status) {
        this.status = status;
    }

    public String getMessage() {
        return message;
    }

    public void setMessage(String message) {
        this.message = message;
    }
    
}