import React from 'react'
import './styles.scss';
import { useAppStore } from '../../store/app-store';
import Button from '../button';
import { faClose } from '@fortawesome/free-solid-svg-icons';

const ModalWrapper = ({ modal }: { modal: React.ReactNode }) => {
  const setModal = useAppStore((state) => state.setModal);

  return (
    <div className="modal-wrapper">
      <div className="modal-wrapper__overlay" onClick={() => setModal(null)} />
      <div className="modal-wrapper__container">
        <div className="modal-wrapper__container-header">
          <Button className="modal-wrapper__container-close" onClick={() => setModal(null)} icon={faClose} />
        </div>
        <div className="modal-wrapper__container-content">
          {modal}
        </div>
      </div>
    </div>
  );
};

export default ModalWrapper;